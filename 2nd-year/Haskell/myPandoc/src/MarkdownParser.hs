{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- MarkdownParser
-}

module MarkdownParser (
    parseHeader,
    parseBody
) where

import Control.Applicative (Alternative(..))
import Control.Monad ( void )
import ParserData ( Parser(), parseChar, parseAnyChar, parseMany, parseSome )
import Document (
    FormattingElement(Code, Italic, Bold),
    Content(..)
    )

parseHeaderString :: Parser String
parseHeaderString = parseMany parseCharInsideStr
    <* parseChar ':' <* parseChar ' '
    where
        parseCharInsideStr = parseEscaped <|> parseNormal
        parseNormal = parseAnyChar [x | x <- ['\32'..'\126'], x /= ':']
        parseEscaped = parseChar '\\'
            *> parseAnyChar ['"', '\\', '/', 'b', 'f', 'n', 'r', 't']

parseString :: Parser String
parseString = parseMany parseCharInsideStr
    where
        parseCharInsideStr = parseEscaped <|> parseNormal
        parseNormal = parseAnyChar [x | x <- ['\32'..'\126'], x /= '\n']
        parseEscaped = parseChar '\\'
            *> parseAnyChar ['"', '\\', '/', 'b', 'f', 'n', 'r', 't']

parseStringUntil :: Char -> Parser String
parseStringUntil stop = parseMany parseCharInsideStr
    where
        parseCharInsideStr = parseEscaped <|> parseNormal
        parseNormal = parseAnyChar [x | x <- ['\32'..'\126'], x /= stop]
        parseEscaped = parseChar '\\'
            *> parseAnyChar ['"', '\\', '/', 'b', 'f', 'n', 'r', 't']

parseTextString :: Parser String
parseTextString = parseMany parseCharInsideStr
    where
        parseCharInsideStr = parseEscaped <|> parseNormal
        parseNormal = parseAnyChar [
                x | x <- ['\32'..'\126'],
                x /= '*', x /= '`', x /= '[', x /= '!'
            ]
        parseEscaped = parseChar '\\'
            *> parseAnyChar ['"', '\\', '/', 'b', 'f', 'n', 'r', 't']

parseKeyValuePair :: Parser (String, String)
parseKeyValuePair = (,) <$> parseHeaderString <*> parseString

parseNewline :: Parser ()
parseNewline = void (parseMany (parseChar '\n'))

parseMarkdownHeader :: Parser [(String, String)]
parseMarkdownHeader = do
        _ <- parseChar '-' *> parseChar '-' *> parseChar '-'
        _ <- parseNewline
        e <- parseMany (parseKeyValuePair <* parseNewline)
        _ <- parseChar '-' *> parseChar '-' *> parseChar '-'
        return e

parseHeader :: Parser [(String, String)]
parseHeader = parseNewline *> parseMarkdownHeader

parseContent :: Int -> Parser Content
parseContent level = parseSection level
    <|> parseCodeBlock
    <|> parseList
    <|> parseParagraph

parseSection :: Int -> Parser Content
parseSection parentLevel = do
    (sectionTitle, level) <- parseSectionHeader
    content <- parseMany (parseNewline *> parseContent level)
    if level > parentLevel + 1
        then return $ nestSections (level - parentLevel - 1)
            sectionTitle content
        else return $ Section sectionTitle content
-- TODO: handle the case where it is lower?

nestSections :: Int -> Maybe String -> [Content] -> Content
nestSections 0 title content = Section title content
nestSections n title content = Section (Just "")
    [nestSections (n - 1) title content]

parseSectionHeader :: Parser (Maybe String, Int)
parseSectionHeader = do
    _ <- parseChar '#'
    hashes <- parseMany (parseChar '#')
    let level = length hashes + 1
    title <- parseChar ' ' *> parseTitle
    return (Just title, level)

parseTitle :: Parser String
parseTitle = do
    title <- parseMany parseTitleChar
    void $ parseChar '\n'
    return title

parseTitleChar :: Parser Char
parseTitleChar = parseAnyChar [x | x <- ['\32'..'\126'], x /= '\n']

parseList :: Parser Content
parseList = do
        e <- parseMany
            (parseChar '-' *> parseChar ' ' *> parseParagraph <* parseNewline)
        if null e
        then fail "error"
        else return $ List e

parseCodeBlock :: Parser Content
parseCodeBlock = do
    void $ parseChar '`' <* parseChar '`' <* parseChar '`' <* parseChar '\n'
    text <- parseParagraph
    void $ parseChar '\n' <* parseChar '`' <* parseChar '`' <* parseChar '`'
    return $ CodeBlock [text]

parseParagraph :: Parser Content
parseParagraph = do
    content <- parseContentWithinParagraph
    if null content
        then return $ Paragraph []
        else return $ Paragraph content

parseInlineFormatting :: Parser Content
parseInlineFormatting =
    Formatting <$> (parseBold <|> parseItalic <|> parseCode)

parseBold :: Parser FormattingElement
parseBold = do
    void $ parseChar '*' *> parseChar '*'
    text <- parseStringUntil '*'
    void $ parseChar '*' *> parseChar '*'
    return $ Bold text

parseItalic :: Parser FormattingElement
parseItalic = do
    void $ parseChar '*'
    text <- parseStringUntil '*'
    void $ parseChar '*'
    return $ Italic text

parseCode :: Parser FormattingElement
parseCode = do
    void $ parseChar '`'
    text <- parseStringUntil '`'
    void $ parseChar '`'
    return $ Code text

parseLink :: Parser Content
parseLink = do
    void $ parseChar '['
    linkText <- parseStringUntil ']'
    void $ parseChar ']'
    void $ parseChar '('
    url <- parseStringUntil ')'
    void $ parseChar ')'
    return $ Link url [Text linkText]

parseImage :: Parser Content
parseImage = do
    void $ parseChar '!' <* parseChar '['
    altText <- parseStringUntil ']'
    void $ parseChar ']' <* parseChar '('
    url <- parseStringUntil ')'
    void $ parseChar ')'
    return $ Image url [Text altText]

parseText :: Parser Content
parseText = do
    text <- parseTextString
    if null text
        then fail "error"
        else return $ Text text

parseContentWithinParagraph :: Parser [Content]
parseContentWithinParagraph =
    parseSome
    (parseInlineFormatting <|> parseLink <|> parseImage <|> parseText)

parseBody :: Parser [Content]
parseBody = parseMany (parseNewline *> parseContent 0)

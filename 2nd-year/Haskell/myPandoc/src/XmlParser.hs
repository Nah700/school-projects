{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- XmlParser
-}

module XmlParser (
    XmlValue(..),
    parseXmlValue,
    parseXmlElement,
    parseXmlText,
    parseAttributes,
    parseString,
    parseQuotedString,
    parseWhitespace
) where

import Control.Applicative (Alternative(..))
import Control.Monad (void)
import ParserData (Parser, parseChar, parseAnyChar, parseMany)

data XmlValue
    = XmlElement String [(String, String)] [XmlValue]
    | XmlText String
    deriving (Show, Eq)

parseXmlValue :: Parser XmlValue
parseXmlValue =
    (parseWhitespace *> parseXmlElement) <|> parseXmlText

parseXmlElement :: Parser XmlValue
parseXmlElement = do
    (tagName, attributes) <- parseStartTag
    _ <- parseWhitespace
    inner <- parseMany parseXmlValue
    _ <- parseWhitespace
    endTag <- parseEndTag
    if endTag == tagName
        then return $ XmlElement tagName attributes inner
        else fail "Mismatched end tag"

parseXmlText :: Parser XmlValue
parseXmlText = XmlText <$> parseString

parseStartTag :: Parser (String, [(String, String)])
parseStartTag = do
    _ <- parseChar '<'
    tagName <- parseTagName
    attributes <- parseAttributes
    _ <- parseChar '>'
    return (tagName, attributes)

parseEndTag :: Parser String
parseEndTag = do
    _ <- parseChar '<'
    _ <- parseChar '/'
    endTagName <- parseTagName
    _ <- parseChar '>'
    return endTagName

parseTagName :: Parser String
parseTagName = parseMany
    (parseAnyChar $ ['a'..'z'] ++ ['A'..'Z'] ++ ['0'..'9'] ++ "_-")

parseAttributes :: Parser [(String, String)]
parseAttributes = parseMany parseAttribute
    where
        parseAttribute = do
            parseWhitespace
            name <- parseTagName
            parseWhitespace
            _ <- parseChar '='
            parseWhitespace
            value <- parseQuotedString
            return (name, value)

parseString :: Parser String
parseString = do
    str <- parseMany (parseAnyChar [x | x <- ['\32'..'\126'],
        x `notElem` "<>"])
    if null str
        then fail "Empty string"
        else return str

parseQuotedString :: Parser String
parseQuotedString = parseChar '"' *>
    parseMany (parseAnyChar [x | x <- ['\32'..'\126'], x `notElem` "\""])
    <* parseChar '"'

parseWhitespace :: Parser ()
parseWhitespace = void (parseMany (parseAnyChar " \t\r\n"))

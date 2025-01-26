{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- XmlToDocument
-}

module XmlToDocument (
    xmlToDocument,
    interpretXmlValue,
    interpretHeader,
    interpretElement,
    parseBodyElement,
    lookupSpecificElem,
    getBodyValues,
    interpretContent
) where

import XmlParser (XmlValue(..), parseXmlValue)
import Document (
    Document(..),
    Header(..),
    Content(..),
    FormattingElement (Bold, Italic, Code)
    )
import ParserData ( Parser(runParser) )

xmlToDocument :: String -> Either String Document
xmlToDocument input = do
    xmlValue <- runXmlParser input
    case interpretXmlValue xmlValue of
        Left err -> Left err
        Right (header, content) -> Right $ Document header content

runXmlParser :: String -> Either String XmlValue
runXmlParser input = case runParser parseXmlValue input of
    Left err -> Left err
    Right (value, _) -> Right value

interpretXmlValue :: XmlValue -> Either String (Header, [Content])
interpretXmlValue (XmlElement "document" _ elems) = do
    header <- interpretHeader elems
    content <- interpretContent elems
    return (header, content)
interpretXmlValue _ = Left "Invalid XML format for document"

interpretHeader :: [XmlValue] -> Either String Header
interpretHeader elems = do
    (attr, v) <- getHeaderValues elems
    titleStr <- getAttributeValue "title" attr
    let authorStr = getSpecificString "author" v
        dateStr = getSpecificString "date" v
    return $ Header titleStr authorStr dateStr

getSpecificString :: String -> [XmlValue] -> Maybe String
getSpecificString s v = case lookupSpecificElem s v of
    Just (XmlElement _ _ [XmlText str]) -> Just str
    _ -> Nothing

getHeaderValues :: [XmlValue] -> Either String ([(String, String)], [XmlValue])
getHeaderValues elems = case filter isHeaderElem elems of
    [XmlElement _ attrs v] -> Right (attrs, v)
    _ -> Left "Header not found"

isHeaderElem :: XmlValue -> Bool
isHeaderElem (XmlElement "header" _ _) = True
isHeaderElem _ = False

getAttributeValue :: String -> [(String, String)] -> Either String String
getAttributeValue key attrs = case lookup key attrs of
    Just value -> Right value
    Nothing -> Left $ "Missing attribute: " ++ key

lookupSpecificElem :: String -> [XmlValue] -> Maybe XmlValue
lookupSpecificElem _ [] = Nothing
lookupSpecificElem key (e@(XmlElement k _ _):others)
    | key == k = Just e
    | otherwise = lookupSpecificElem key others
lookupSpecificElem _ _ = Nothing

getBodyValues :: [XmlValue] -> Either String [XmlValue]
getBodyValues elems = case filter isBodyElem elems of
    [XmlElement _ _ v] -> Right v
    _ -> Left "body not found"

isBodyElem :: XmlValue -> Bool
isBodyElem (XmlElement "body" _ _) = True
isBodyElem _ = False

interpretContent :: [XmlValue] -> Either String [Content]
interpretContent elems = do
    v <- getBodyValues elems
    mapM interpretElement v

interpretElement :: XmlValue -> Either String Content
interpretElement (XmlElement "paragraph" _ i) = Paragraph <$> parseBody i
interpretElement (XmlElement "section" attrs i) = parseSection attrs i
interpretElement (XmlElement "codeblock" _ i) = CodeBlock <$> parseCodeBlock i
interpretElement (XmlElement "list" _ i) = List <$> parseList i
interpretElement (XmlElement "bold" _ i) = parseFormattedText "bold" i
interpretElement (XmlElement "italic" _ i) = parseFormattedText "italic" i
interpretElement (XmlElement "code" _ i) = parseFormattedText "code" i
interpretElement (XmlElement "link" attrs i) = parseLink attrs i
interpretElement (XmlElement "image" attrs i) = parseImage attrs i
interpretElement (XmlText s) = Right $ Text s
interpretElement _ = Left "Invalid XML element"

parseBody :: [XmlValue] -> Either String [Content]
parseBody = mapM parseBodyElement

parseBodyElement :: XmlValue -> Either String Content
parseBodyElement (XmlText str) = Right $ Text str
parseBodyElement e = interpretElement e

parseSection :: [(String, String)] -> [XmlValue] -> Either String Content
parseSection attrs inner = do
    let titleStr = lookup "title" attrs
    content <- mapM interpretElement inner
    return $ Section titleStr content

parseCodeBlock :: [XmlValue] -> Either String [Content]
parseCodeBlock = mapM interpretElement

parseList :: [XmlValue] -> Either String [Content]
parseList = mapM interpretElement

parseFormattedText :: String -> [XmlValue] -> Either String Content
parseFormattedText format inner =
    let text = concat <$> mapM parseFormattedTextContent inner
    in case text of
        Just t -> case format of
            "bold" -> Right $ Formatting (Bold t)
            "italic" -> Right $ Formatting (Italic t)
            "code" -> Right $ Formatting (Code t)
            _ -> Left "invalid formating type"
        Nothing -> Left "Invalid formatted text content"

parseFormattedTextContent :: XmlValue -> Maybe String
parseFormattedTextContent (XmlText str) = Just str
parseFormattedTextContent _ = Nothing

parseLink :: [(String, String)] -> [XmlValue] -> Either String Content
parseLink attrs inner = do
    url <- getAttributeValue "url" attrs
    content <- mapM interpretElement inner
    return $ Link url content

parseImage :: [(String, String)] -> [XmlValue] -> Either String Content
parseImage attrs inner = do
    url <- getAttributeValue "url" attrs
    content <- mapM parseBodyElement inner
    return $ Image url content

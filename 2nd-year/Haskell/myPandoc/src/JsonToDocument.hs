{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- JsonToDocument
-}

module JsonToDocument (
    jsonToDocument
) where

import ParserData ( Parser(runParser) )
import JsonParser ( JsonValue(..), parseJsonValue )
import Document
    ( FormattingElement(Code, Italic, Bold),
      Content(..),
      Header(Header),
      Document(..) )

jsonToDocument :: String -> Either String Document
jsonToDocument input = do
    jsonValue <- runJsonParser input
    case interpretJsonValue jsonValue of
        Left err -> Left err
        Right (header, content) -> Right $ Document header content

runJsonParser :: String -> Either String JsonValue
runJsonParser input = case runParser parseJsonValue input of
    Left err -> Left err
    Right (value, _) -> Right value

interpretJsonValue :: JsonValue -> Either String (Header, [Content])
interpretJsonValue (JsonObject obj) = do
    headerObject <- lookupObject "header" obj
    contentArray <- lookupArray "body" obj
    header <- interpretHeader headerObject
    content <- interpretContent contentArray
    return (header, content)
interpretJsonValue _ = Left "Invalid JSON format for document"

interpretHeader :: [(String, JsonValue)] -> Either String Header
interpretHeader obj = do
    titleStr <- lookupString "title" obj
    let authorStr = lookupOptionalString "author" obj
    let dateStr = lookupOptionalString "date" obj
    return $ Header titleStr authorStr dateStr

interpretContent :: [JsonValue] -> Either String [Content]
interpretContent = mapM interpretVal

interpretVal :: JsonValue -> Either String Content
interpretVal  (JsonString str) = Right $ Text str
interpretVal (JsonObject [obj@("bold", JsonString _)]) = parseFormatting obj
interpretVal (JsonObject [obj@("italic", JsonString _)]) = parseFormatting obj
interpretVal (JsonObject [obj@("code", JsonString _)]) = parseFormatting obj
interpretVal (JsonObject [("link", JsonObject obj)]) = parseLink obj
interpretVal (JsonObject [("image", JsonObject obj)]) = parseImage obj
interpretVal (JsonArray arr) = Paragraph <$> parseBody arr
interpretVal (JsonObject [("section", JsonObject obj)]) = parseSection obj
interpretVal (JsonObject [("codeblock", JsonArray arr)]) = parseCodeBlock arr
interpretVal (JsonObject [("list", JsonArray arr)]) =
        List <$> mapM interpretVal arr
interpretVal _ = Left "Error"

parseFormatting :: (String, JsonValue) -> Either String Content
parseFormatting ("italic", JsonString str) = Right $ Formatting (Italic str)
parseFormatting ("bold", JsonString str) = Right $ Formatting (Bold str)
parseFormatting ("code", JsonString str) = Right $ Formatting (Code str)
parseFormatting _ = Left "Invalid formatting format"

parseBody :: [JsonValue] -> Either String [Content]
parseBody = mapM parseBodyElement

parseBodyElement :: JsonValue -> Either String Content
parseBodyElement (JsonString str) = Right $ Text str
parseBodyElement obj@(JsonObject _) = interpretVal obj
parseBodyElement _ = Left "Invalid body element format"

parseLink :: [(String, JsonValue)] -> Either String Content
parseLink obj = do
    url <- lookupString "url" obj
    content <- case lookup "content" obj of
        Just (JsonArray contentObj) -> interpretContent contentObj
        _ -> Left "Error"
    return $ Link url content

parseImage :: [(String, JsonValue)] -> Either String Content
parseImage obj = do
    url <- lookupString "url" obj
    content <- case lookup "alt" obj of
        Just (JsonArray contentObj) -> interpretContent contentObj
        _ -> Left "Error"
    return $ Image url content

parseSection :: [(String, JsonValue)] -> Either String Content
parseSection obj = do
    let titleStr = lookupOptionalString "title" obj
    content <- case lookup "content" obj of
        Just (JsonArray contentObj) -> interpretContent contentObj
        _ -> Left "Error"
    return $ Section titleStr content

parseCodeBlock :: [JsonValue] -> Either String Content
parseCodeBlock obj = do
    codeLines <- mapM interpretVal obj
    return $ CodeBlock codeLines

lookupString :: String -> [(String, JsonValue)] -> Either String String
lookupString key obj =
    case lookup key obj of
        Just (JsonString value) -> Right value
        _ -> Left $ "Missing or invalid value for key: " ++ key

lookupOptionalString :: String -> [(String, JsonValue)] -> Maybe String
lookupOptionalString key obj =
    case lookup key obj of
        Just (JsonString value) -> Just value
        _ -> Nothing

lookupObject :: String -> [(String, JsonValue)] ->
    Either String [(String, JsonValue)]
lookupObject key obj =
    case lookup key obj of
        Just (JsonObject o) -> Right o
        _ -> Left $ "Missing or invalid value for key: " ++ key

lookupArray :: String -> [(String, JsonValue)] -> Either String [JsonValue]
lookupArray key obj =
    case lookup key obj of
        Just (JsonArray a) -> Right a
        _ -> Left $ "Missing or invalid value for key: " ++ key

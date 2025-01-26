{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- JsonParser
-}

module JsonParser (
    JsonValue(..),
    parseObject,
    parseArray,
    parseString,
    parseWhitespace,
    parseJsonString,
    parseJsonValue,
) where

import Control.Applicative (Alternative(..))
import Control.Monad ( void )
import ParserData ( Parser, parseChar, parseAnyChar, parseMany )

data JsonValue
    = JsonString String
    | JsonArray [JsonValue]
    | JsonObject [(String, JsonValue)]
    deriving (Show, Eq)

parseString :: Parser String
parseString = parseChar '"' *> parseMany parseCharInsideStr <* parseChar '"'
    where
        parseCharInsideStr = parseEscaped <|> parseDoubleQuote <|> parseNormal
        parseNormal = parseAnyChar [x | x <- ['\32'..'\126'], x /= '"']
        parseEscaped = parseChar '\\'
            *> parseAnyChar ['"', '\\', '/', 'b', 'f', 'n', 'r', 't']
        parseDoubleQuote = parseChar '\\' *> parseChar '"'

parseJsonString :: Parser JsonValue
parseJsonString = JsonString <$> parseString

parseArray :: Parser JsonValue
parseArray = JsonArray <$> (parseChar '[' *> parseElems <* parseChar ']')
    where
        parseElems = ((:) <$> parseJsonValue <*> parseMoreElems) <|> pure []
        parseMoreElems = parseMany
            ((parseChar ',' *> parseJsonValue) <* parseWhitespace)

parseObject :: Parser JsonValue
parseObject = JsonObject <$>
    (
        parseChar '{' *> parseWhitespace *> parseElems
        <* parseWhitespace <* parseChar '}'
    )
    where
        parseElems = ((:) <$> parseKeyValuePair <*> parseMoreElems) <|> pure []
        parseMoreElems = parseMany
            ((parseChar ',' *> parseWhitespace *>
            parseKeyValuePair) <* parseWhitespace)

parseKeyValuePair :: Parser (String, JsonValue)
parseKeyValuePair = (,) <$> (parseString <* parseChar ':') <*> parseJsonValue

parseJsonValue :: Parser JsonValue
parseJsonValue =
    parseWhitespace *>
    (parseJsonString <|> parseArray <|> parseObject)
    <* parseWhitespace

parseWhitespace :: Parser ()
parseWhitespace = void (parseMany (parseAnyChar " \t\r\n"))

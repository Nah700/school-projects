{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- ParserData
-}

module ParserData (
    Parser(..),
    parseChar,
    parseAnyChar,
    parseOr,
    parseAnd,
    parseAndWith,
    parseMany,
    parseSome,
    parseUInt,
    parseInt,
    parseUDouble,
    parseDouble,
    parseTuple,
    parseTruple,
    someone
) where

import Control.Applicative (Alternative(..), many, some, liftA2, optional)

newtype Parser a = Parser {
    runParser :: String -> Either String (a , String )
}

instance Functor Parser where
    fmap f (Parser p) = Parser $ \input ->
        case p input of
            Left err -> Left err
            Right (result, remaining) -> Right (f result, remaining)

instance Applicative Parser where
    pure x = Parser $ \input -> Right (x, input)

    p1 <*> p2 = Parser $ \input ->
        case runParser p1 input of
            Left err1 -> Left err1
            Right (f, remaining1) ->
                case runParser p2 remaining1 of
                    Left err2 -> Left err2
                    Right (x, remaining2) -> Right (f x, remaining2)

instance Alternative Parser where
    empty = Parser $ \_ -> Left "Parse error"
    (Parser p1) <|> (Parser p2) = Parser $ \input ->
        case p1 input of
            Left _ -> p2 input
            result -> result

instance Monad Parser where
    return = pure
    (Parser p) >>= f = Parser $ \input ->
        case p input of
            Left err -> Left err
            Right (result, remaining) ->
                let (Parser g) = f result
                in g remaining

instance MonadFail Parser where
    fail = Parser . const . Left

parseChar :: Char -> Parser Char
parseChar c = Parser $ \input ->
    case input of
        (x:xs) -> if c == x
                    then Right (x, xs)
                    else Left $ "Char '" ++ [c] ++ "' not found"
        _ -> Left "Empty input"

parseAnyChar :: String -> Parser Char
parseAnyChar = foldr ((<|>) . parseChar) empty

parseOr :: Parser a -> Parser a -> Parser a
parseOr = (<|>)

parseAnd :: Parser a -> Parser b -> Parser (a, b)
parseAnd = liftA2 (,)

parseAndWith :: (a -> b -> c) -> Parser a -> Parser b -> Parser c
parseAndWith = liftA2

parseMany :: Parser a -> Parser [a]
parseMany = many

parseSome :: Parser a -> Parser [a]
parseSome = some

parseUInt :: Parser Int
parseUInt = read <$> parseSome (parseAnyChar ['0'..'9'])

parseInt :: Parser Int
parseInt = (negate <$> (parseChar '-' *> parseUInt)) <|> parseUInt

parseUDouble :: Parser Double
parseUDouble = read <$> parseSome (parseAnyChar ['0'..'9'])

parseDouble :: Parser Double
parseDouble = do
    intPart <- parseInt
    fractionalPart <- optionalFractionalPart
    case fractionalPart of
        Nothing -> return $ fromIntegral intPart
        Just frac -> return $ fromIntegral intPart + frac
  where
    optionalFractionalPart :: Parser (Maybe Double)
    optionalFractionalPart = optional (parseChar '.' *> parseUInt
        >>= \frac -> return $ fromIntegral frac / 10 ^ length (show frac))

parseTuple :: Parser a -> Parser (a, a)
parseTuple p = (,) <$> (parseChar '(' *> p)
    <*> (parseChar ',' *> p <* parseChar ')')

parseTruple :: Parser (Int, Int, Int)
parseTruple = (,,) <$> (parseChar '(' *> parseInt)
    <*> (parseChar ',' *> parseInt)
    <*> (parseChar ',' *> parseInt <* parseChar ')')

someone :: Parser a -> Parser [a]
someone p = (:) <$> p <*> many p

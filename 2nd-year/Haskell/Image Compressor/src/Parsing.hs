{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-compressor-nahim.kandari
-- File description:
-- Parsing
-}

module Parsing (parseArgs,
                parseFile,
                ) where

import Includes

import Options.Applicative
import Utilityfunctions(clearChar, cleanStr)

parseArgs :: Parser Vectors
parseArgs = Vectors
    <$> option auto (short 'n' <> metavar "N")
    <*> option auto (short 'l' <> metavar "L")
    <*> option str (short 'f' <> metavar "F")

convertToPoints :: [TheFile] -> [Point]
convertToPoints [] = []
convertToPoints (x:xs) = case x of
    Left BadPoint -> []
    Right Point {position = Position (a, y), color = Color (r, g, b)} ->
        Point {position = Position (a, y), color = Color (r, g, b)} :
        convertToPoints xs

isNotAPoint :: [TheFile] -> Bool
isNotAPoint [] = False
isNotAPoint (x:xs) = case x of
    Left BadPoint -> True
    Right _ -> isNotAPoint xs

getPixelColor :: [String] -> TheFile
getPixelColor (x:y:r:g:b:_)
    | not $ all (\val -> (val :: Int) >= 0 && (val :: Int) <= 255)
    [vr, vg, vb] = Left BadPoint
    | otherwise = Right Point {position = Position (read x :: Int, read y ::
    Int), color = Color (read r :: Int, read g :: Int, read b :: Int)}
    where
        vr = read r
        vg = read g
        vb = read b
getPixelColor _ = Left BadPoint

getTheLine :: String -> TheFile
getTheLine line
    | length (words line) /= 5 = Left BadPoint
    | otherwise = getPixelColor (words line)

parsePoints :: [String] -> [Point]
parsePoints line
    | isNotAPoint content = []
    | otherwise = convertToPoints content
    where
        content = map getTheLine line

parseFile :: String -> [Point]
parseFile content = parsePoints $ map clearChar $ words (cleanStr content)
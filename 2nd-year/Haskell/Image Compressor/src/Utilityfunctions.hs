{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-compressor-nahim.kandari
-- File description:
-- Utilityfunctions
-}

module Utilityfunctions (isNumber,
                        cleanStr,
                        clearChar,
                        calculateDistance
                        ) where

import Includes

isNumber :: Char -> Bool
isNumber c = c `elem` ['0'..'9']

cleanStr :: String -> String
cleanStr xs = [x | x <- xs, x `notElem` " "]

clearChar :: String -> String
clearChar [] = []
clearChar (x:xs)
    | not (isNumber x) = ' ' : clearChar xs
    | otherwise = x:clearChar xs

calculateDistance :: Color -> Color -> Float
calculateDistance (Color (x1, y1, z1)) (Color (x2, y2, z2)) = sqrt $
    fromIntegral ((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)

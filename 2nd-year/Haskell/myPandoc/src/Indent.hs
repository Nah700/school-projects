{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- Indent
-}

module Indent (
    generateIndent,
    addIndent,
    escapeString
) where

generateIndent :: Int -> String
generateIndent level = replicate (level * 4) ' '

addIndent :: Int -> String -> String
addIndent level line = generateIndent level ++ line

escapeString :: String -> String
escapeString = concatMap escapeChar
  where
    escapeChar '\\' = "\\\\"
    escapeChar '\"' = "\\\""
    escapeChar c = [c]

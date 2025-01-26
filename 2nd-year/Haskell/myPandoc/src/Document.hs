{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- Document
-}

module Document (
    Document(..),
    Header(..),
    Content(..),
    FormattingElement(..),
) where

data Document = Document Header [Content]
    deriving (Show, Eq)

data Header = Header {
    title :: String,
    author :: Maybe String,
    date :: Maybe String
} deriving (Show, Eq)

data Content
    = Text String
    | Formatting FormattingElement
    | Link String [Content]
    | Image String [Content]
    | Paragraph [Content]
    | Section (Maybe String) [Content]
    | CodeBlock [Content]
    | List [Content]
    deriving (Show, Eq)

data FormattingElement
    = Italic String
    | Bold String
    | Code String
    deriving (Show, Eq)

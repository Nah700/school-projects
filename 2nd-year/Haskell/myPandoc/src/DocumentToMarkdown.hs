{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- DocumentToMarkdown
-}

module DocumentToMarkdown (
    documentToMarkdown,
    headerToMarkdown,
    contentToMarkdown,
    contentToMarkdownArray
) where

import Data.List (intercalate)
import Document
    ( Document(..),
    Header(..),
    Content(..),
    FormattingElement(..) )

headerToMarkdown :: Header -> String
headerToMarkdown (Header titleStr au da) =
    "---\n" ++
    "title: " ++ titleStr ++
    maybe "" (mappend "\nauthor: ") au ++
    maybe "" (mappend "\ndate: ") da ++
    "\n---\n\n"

contentToMarkdown :: Int -> Content -> String
contentToMarkdown _ (Text str) = str
contentToMarkdown _ (Formatting (Italic str)) = "*" ++ str ++ "*"
contentToMarkdown _ (Formatting (Bold str)) = "**" ++ str ++ "**"
contentToMarkdown _ (Formatting (Code str)) = "`" ++ str ++ "`"
contentToMarkdown level (Link url content) = "[" ++
    contentToMarkdown level (Paragraph content) ++ "](" ++ url ++ ")"
contentToMarkdown level (Image url alt) = "![" ++ contentToMarkdown level
    (Paragraph alt) ++ "](" ++ url ++ ")"
contentToMarkdown level (Paragraph content) = concatMap
    (contentToMarkdown level) content
contentToMarkdown level (Section simpletitle content) =
    (case simpletitle of
        Just t  -> if t /= "" then replicate level '#' ++ " " ++ t ++ "\n\n"
        else ""
        Nothing -> "")
    ++ intercalate "\n" (fmap (contentToMarkdown (level+1)) content)
contentToMarkdown level (CodeBlock codeLines) = "```\n" ++ intercalate "\n"
    (fmap (contentToMarkdown level) codeLines) ++ "\n```"
contentToMarkdown level (List items) = intercalate "\n" (
    fmap (\item -> "- " ++ contentToMarkdown level item) items)

contentToMarkdownArray :: [Content] -> String
contentToMarkdownArray content = intercalate "\n" (
    fmap (contentToMarkdown 1) content)

documentToMarkdown :: Document -> String
documentToMarkdown (Document header content) =
    headerToMarkdown header ++ contentToMarkdownArray content

{-
-- EPITECH PROJECT, 2024
-- B-FUN-400-STG-4-1-mypandoc-noe.tritsch
-- File description:
-- DocumentToXmlSpec
-}

module DocumentToXmlSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, Spec )
import Document
    ( Content(Text, Formatting, Link, Image, Paragraph, Section, CodeBlock, List),
      Document(Document),
      FormattingElement(Italic, Bold, Code),
      Header(Header) )
import DocumentToXml ( documentToXml )

spec :: Spec
spec = do
    describe "Document to XML conversion" $ do
        it "should convert a document with header and text content to XML" $
            let doc = Document (Header "Title" (Just "Author") (Just "Date")) [Text "Some text"]
                expectedXml = "<document>\n\
                              \    <header title=\"Title\">\n\
                              \        <author>Author</author>\n\
                              \        <date>Date</date>\n\
                              \    </header>\n\
                              \    <body>Some text\n\
                              \    </body>\n\
                              \</document>"
            in documentToXml doc `shouldBe` expectedXml

        it "should convert a document with header and formatting element to XML" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Italic "Italic text")]
                expectedXml = "<document>\n\
                              \    <header title=\"Title\">\n\
                              \    </header>\n\
                              \    <body><italic>Italic text</italic>\n\
                              \    </body>\n\
                              \</document>"
            in documentToXml doc `shouldBe` expectedXml

        it "should convert a document with header and link to XML" $
            let doc = Document (Header "Title" Nothing Nothing) [Link "https://example.com" [Text "Link text"]]
                expectedXml = "<document>\n\
                              \    <header title=\"Title\">\n\
                              \    </header>\n\
                              \    <body><link url=\"https://example.com\">Link text</link>\n\
                              \    </body>\n\
                              \</document>"
            in documentToXml doc `shouldBe` expectedXml

    describe "Content Cases" $ do
        it "should handle Text content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Text "Some text"]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body>Some text\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Italic formatting content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Italic "Italic text")]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body><italic>Italic text</italic>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Bold formatting content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Bold "Bold text")]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body><bold>Bold text</bold>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Code formatting content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Code "Code text")]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body><code>Code text</code>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Link content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Link "https://example.com" [Text "Link text"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body><link url=\"https://example.com\">Link text</link>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Image content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Image "image.jpg" [Text "Alt text"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body><image url=\"image.jpg\">Alt text</image>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Paragraph content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Paragraph [Text "Paragraph content"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body>\n\
                               \        <paragraph>Paragraph content</paragraph>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle Section content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [Section (Just "Section title") [Text "Section content"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body>\n\
                               \        <section title=\"Section title\">Section content\n\
                               \        </section>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle CodeBlock content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [CodeBlock [Text "Line 1", Text "Line 2"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body>\n\
                               \        <codeblock>Line 1Line 2\n\
                               \        </codeblock>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

        it "should handle List content" $ do
            let doc = Document (Header "Title" Nothing Nothing) [List [Text "Item 1", Text "Item 2"]]
                expectedXml = "<document>\n\
                               \    <header title=\"Title\">\n\
                               \    </header>\n\
                               \    <body>\n\
                               \        <list>Item 1Item 2\n\
                               \        </list>\n\
                               \    </body>\n\
                               \</document>"
            documentToXml doc `shouldBe` expectedXml

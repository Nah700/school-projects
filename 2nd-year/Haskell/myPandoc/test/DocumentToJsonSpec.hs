module DocumentToJsonSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, Spec )
import Document
    ( Content(..),
      Document(..),
      FormattingElement(..),
      Header(..) )
import DocumentToJson ( documentToJson )

spec :: Spec
spec = do
    describe "Document to JSON conversion" $ do

        it "should convert a document with formatting element to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Bold "Bold text")]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"bold\": \"Bold text\"\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with image to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Image "image.jpg" [Text "Alt text"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"image\": {\n                \"url\": \"image.jpg\",\n                \"alt\": [\n                    \"Alt text\"\n                ]\n            }\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with link to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Link "link.com" [Text "Alt text"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"link\": {\n                \"url\": \"link.com\",\n                \"content\": [\n                    \"Alt text\"\n                ]\n            }\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with paragraph to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Paragraph [Text "Paragraph content"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        [\n            \"Paragraph content\"\n        ]\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with section to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Section (Just "Section title") [Text "Section content"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"section\": {\n                \"title\": \"Section title\",\n                \"content\": [\n                    \"Section content\"\n                ]\n            }\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with code block to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [CodeBlock [Text "Line 1", Text "Line 2"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"codeblock\": [\n                \"Line 1\",\n                \"Line 2\"\n            ]\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with list to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [List [Text "Item 1", Text "Item 2"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"list\": [\n                \"Item 1\",\n                \"Item 2\"\n            ]\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with empty list to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [List []]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"list\": [\n\n            ]\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a normal document with list to JSON" $
            let doc = Document (Header "Title" (Just "one") (Just "two")) [List [Text "Item 1", Text "Item 2"]]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n        \"author\": \"one\",\n        \"date\": \"two\"\n    },\n    \"body\": [\n        {\n            \"list\": [\n                \"Item 1\",\n                \"Item 2\"\n            ]\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with italic formatting to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Italic "Italic text")]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"italic\": \"Italic text\"\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with bold formatting to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Bold "Bold text")]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"bold\": \"Bold text\"\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

        it "should convert a document with code formatting to JSON" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Code "Code text")]
                expectedJson = "{\n    \"header\": {\n        \"title\": \"Title\",\n    },\n    \"body\": [\n        {\n            \"code\": \"Code text\"\n        }\n    ]\n}"
            in documentToJson doc `shouldBe` expectedJson

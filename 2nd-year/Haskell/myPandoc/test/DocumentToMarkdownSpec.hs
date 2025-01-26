module DocumentToMarkdownSpec (spec) where

import Test.Hspec ( describe, it, shouldBe, Spec )
import Document
    ( Content(..),
      Document(..),
      FormattingElement(..),
      Header(..) )
import DocumentToMarkdown (
        documentToMarkdown,
        headerToMarkdown,
        contentToMarkdown,
        contentToMarkdownArray
    )

spec :: Spec
spec = do
    describe "Document to Markdown conversion" $ do
        it "should convert a document with header and text content to Markdown" $
            let doc = Document (Header "Title" (Just "Author") (Just "Date")) [Text "Some text"]
                expectedMarkdown = "---\ntitle: Title\nauthor: Author\ndate: Date\n---\n\nSome text"
            in documentToMarkdown doc `shouldBe` expectedMarkdown

        it "should convert a header with only a title to Markdown" $
            let header = Header "Title" Nothing Nothing
                expectedMarkdown = "---\ntitle: Title\n---\n\n"
            in headerToMarkdown header `shouldBe` expectedMarkdown

        it "should convert a Formatting (Bold) element to Markdown" $
            let boldContent = Formatting (Bold "Bold text")
                expectedMarkdown = "**Bold text**"
            in contentToMarkdown 1 boldContent `shouldBe` expectedMarkdown

        it "should convert a list of content to a Markdown array" $
            let contents = [Text "Text content", Formatting (Italic "Italic text")]
                expectedMarkdown = "Text content\n*Italic text*"
            in contentToMarkdownArray contents `shouldBe` expectedMarkdown

        it "should convert a document with header and formatting element to Markdown" $
            let doc = Document (Header "Title" Nothing Nothing) [Formatting (Italic "Italic text")]
                expectedMarkdown = "---\ntitle: Title\n---\n\n*Italic text*"
            in documentToMarkdown doc `shouldBe` expectedMarkdown

    describe "contentToMarkdown" $ do
        it "should convert plain text to Markdown" $
            let content = Text "Some text"
                expectedMarkdown = "Some text"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert italic formatted text to Markdown" $
            let content = Formatting (Italic "Italic text")
                expectedMarkdown = "*Italic text*"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert bold formatted text to Markdown" $
            let content = Formatting (Bold "Bold text")
                expectedMarkdown = "**Bold text**"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert code formatted text to Markdown" $
            let content = Formatting (Code "Code text")
                expectedMarkdown = "`Code text`"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert a link to Markdown" $
            let content = Link "https://example.com" [Text "Link text"]
                expectedMarkdown = "[Link text](https://example.com)"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert an image to Markdown" $
            let content = Image "image.jpg" [Text "Alt text"]
                expectedMarkdown = "![Alt text](image.jpg)"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert a paragraph to Markdown" $
            let content = Paragraph [Text "Paragraph content"]
                expectedMarkdown = "Paragraph content"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert a section to Markdown" $
            let content = Section (Just "Section title") [Text "Section content"]
                expectedMarkdown = "# Section title\n\nSection content"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert a code block to Markdown" $
            let content = CodeBlock [Text "Line 1", Text "Line 2"]
                expectedMarkdown = "```\nLine 1\nLine 2\n```"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

        it "should convert a list to Markdown" $
            let content = List [Text "Item 1", Text "Item 2"]
                expectedMarkdown = "- Item 1\n- Item 2"
            in contentToMarkdown 1 content `shouldBe` expectedMarkdown

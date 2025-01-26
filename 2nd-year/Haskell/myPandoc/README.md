MyPandoc Haskell Project
=====================

About
-----

Pandoc is a free and open-source document converter that supports numerous text file formats. This project is a simplified version of Pandoc, implemented in Haskell. The goal is to create a program that can interact with documents and convert them from one format to another.
It supports the conversion of documents between XML, JSON, and Markdown formats. This project is a part of the 400-level Functional Programming course at EPITECH.


Installation
-----------

To install MyPandoc, you need to have Stack (version 2.1.3 or higher) installed on your system. Once you have Stack installed, follow these steps:

Clone the repository:
```
git clone https://github.com/EpitechPromo2027/B-FUN-400-STG-4-1-mypandoc-noe.tritsch
```

Navigate to the project directory:
```
cd mypandoc
```

Build the project:
```
make
```

Usage
----

To use MyPandoc, you need to provide input and output files along with the desired input and output formats. Here's the basic usage:
```
./mypandoc -i input_file -f output_format [-o output_file] [-e input_format]
```


Document Structure
-----------------

A document is described as an organized structure of information, defined by a set of syntactic rules. This structure comprises two main parts: the header and the content.

1. **Header**:
	* Title: A document has a title.
	* Author (Optional): An optional field to indicate the document's author.
	* Date (Optional): An optional field to specify the creation date.
2. **Content**:
	* The main body of the document is made up of various elements:
		+ Text: A sequence of ASCII characters.
		+ Formatting:
			- Italic.
			- Bold.
			- Code.
		+ Links and Images:
			- Link: Composed of text and additional content.
			- Image: Composed of text and additional content.
		+ Structural Elements:
			- Paragraph: A grouping of content elements forming a paragraph.
			- Section: A section with an optional title, containing more content.
			- Code Block: A block of code.
		+ List Elements:
			- List: Composed of items.
			- Item: Represents an individual item in a list, composed of various content elements.

Supported Formats
-----------------

The program can handle three formats: XML, JSON, and Markdown. Each format has its own way to represent a document. The project does not require implementing the full specifications of these formats, but only the parts relevant to this project.

1. **XML**: Extensible Markup Language (XML) is a markup language and file format for storing, transmitting, and reconstructing arbitrary data. [Learn more](https://developer.mozilla.org/en-US/docs/Web/XML/XML_introduction)
2. **JSON**: JSON (JavaScript Object Notation) is a lightweight data-interchange format which is a subset of the JavaScript language. [Learn more](https://www.json.org/json-en.html)
3. **Markdown**: Markdown is a lightweight markup language for creating formatted text using a plain-text editor. [Learn more](https://www.markdownguide.org/basic-syntax)

Parser
------

The project has implemented a parsing library to help with parsing the different file formats. The parser transforms the input file into a Document.

Running the Program
------------------

The program support the following options:

* `-i`: path to input file (mandatory)
* `-f`: format of the output
* `-o`: path to the output file
* `-e`: format of the input file

If no option or invalid options are provided, the program return 84 and display a usage message. If no output file is provided, the program output the result on the standard output. If no input format is provided, the program detect the format.

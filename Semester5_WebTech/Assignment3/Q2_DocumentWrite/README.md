# Assignment 2: External JavaScript with `document.write()`

## How to Run
Simply double-click or open `index.html` in any modern web browser.

## Concept Explanations

### 1. What is `document.write()` and its history?
`document.write()` is a method in JavaScript that writes a string of text directly to the document stream opened by `document.open()`. It is one of the oldest methods in the DOM (Document Object Model) API, dating back to the early days of JavaScript (Netscape Navigator 2). It was primarily used to dynamically generate parts of a web page before modern DOM manipulation methods (like `createElement`, `appendChild`, or `innerHTML`) existed.

### 2. Why is it considered deprecated?
For modern web development, `document.write()` is heavily discouraged for several reasons:
- **Performance:** It blocks the HTML parser. The browser must pause parsing the HTML document to execute the script and insert the written content, which slows down page loading.
- **Destructive Behavior:** If `document.write()` is called *after* the page has fully loaded (i.e., after the document stream is closed), it will implicitly call `document.open()` which clears the entire existing document, erasing everything on the page.
- **Modern Alternatives:** Methods like DOM manipulation, `fetch` for loading data asynchronously, and modern frameworks (React, Angular) offer much more efficient and controlled ways to update the UI dynamically.
- However, it is still valid and useful for educational purposes to understand how the browser parses and builds a page.

### 3. External JS vs. Inline JS
- **Inline JS:** JavaScript code written directly within an HTML file inside `<script>` and `</script>` tags, or as inline event handlers (like `onclick="doSomething()"`). It clutters the HTML and is harder to maintain.
- **External JS:** JavaScript code written in a separate file (e.g., `.js` extension) and linked in the HTML using the `<script src="filename.js"></script>` tag. 
  - **Benefits:** Clean separation of concerns (HTML for structure, JS for logic), reusability across multiple HTML pages, and better caching by the browser.

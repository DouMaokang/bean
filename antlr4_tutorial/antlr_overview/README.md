# Parsing Terms
![](../resources/Screenshot%202022-08-28%20at%2012.09.13%20AM.png)

# Parse Trees
- `CharStream`
- `Lexer`
- `Token`
- `TokenStream`
- `Parser`
- `ParseTree`
  - Subclasses:
    - `RuleNode`
      - Not specific to a particular grammar.
      - Method: `getChild()`, `getParent()`
      - Subclasses: context objects (Each context object knows the start and stop tokens for the recognized phrase and provide access to all the elements of that phrase)
        - `StatContext`
        - `AssignContext`
        - `ExprContext`
        - ...
    - `TerminalNode`

![](../resources/Screenshot%202022-08-27%20at%2011.44.24%20PM.png)
![](../resources/Screenshot%202022-08-27%20at%2011.49.52%20PM.png)


# Listeners and Visitors
Two tree-walking mechanisms are provided in antlr runtime

## Parse-Tree Listeners
- The listener interface responds to events triggered by the built-in tree walker.
- Methods in a listener are callbacks (all automatic).
- `ParseTreeWalker`: to walk a tree and trigger calls into a listener.
- Antlr generates a `ParseTreeListener` subclass specific to each grammar with enter and exit methods for each rule.

![](../resources/Screenshot%202022-08-28%20at%2012.02.19%20AM.png)
![](../resources/Screenshot%202022-08-28%20at%2012.02.33%20AM.png)

## Parse-Tree Visitor
- To control the tree walk and explicitly call methods to visit children.
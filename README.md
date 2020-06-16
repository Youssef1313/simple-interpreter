# Welcome to our simple interpreter

## General idea

This is a simple interpreter written in C++ that has the following features:

- Variables
- Expression evaluation
- If statements
- Goto statements
- Comments
- Text editor with syntax highlighting

**Note:** This project is done using CLion, CMake, and Qt. If you don't have any of these installed, most likely you won't be able to compile it.

**Note2:** There is already a compiled version in the *EXE* folder.

## Syntax

### Comments

To write a comment, you use the hash `#` sign followed by your comment.

```
# This is a comment.
<SOME_CODE> # This is a comment too.
```

### How to declare a variable

To declare a variable, you do the following:

```
variableName = 5     # This is stored as an integer.
variableName2 = 5.0  # This is stored as a double.
variableName3 = true # This is stored as a boolean.
```

Variable values can be expressions as well:

```
two = 2
variableName = 5 + two * 3 # The value will be 11
```

#### Variable naming rules

1. Variable name must start with a letter or `_`.
2. Variable name can contain letters, underscores, or digits.
3. Variable name cannot be a reserved word.

**Note:** Names are case-sensitive.

### Supported operators

The following are the operators starting with the highest precedence to the lowest. Operators mentioned together have the same precedence.

1. The power `x ^ y` operator.

    It returns the value of its left operand raised to the power of its right operand. It's right-associative, which means `2 ^ 1 ^ 3` is evaluated as `2 ^ (1 ^ 3)`.

    Both operands must be of a numeric type (either int or double).

    This operator always returns a double, even if both `x` and `y` are integers.

2. The unary minus `-x` and unary plus `+x` operators.

    The unary minus returns the negative value of `x`, the unary plus returns the value of `x`.

    The operand must be of a numeric type (either int or double).

    These operators return an integer if `x` is integer, or a double if `x` is double.

3. The multiplication `*` and division `/` operators.

    They return the value of the left operand multiplied/divided by the right operand. They're evaluated from left-to-right.

    The operands must be of a numeric type (either int or double).

    These operators return an integer if and only if **both** operands are integers. Otherwise, returns double.

    **Note:** `5 / 2` returns `2`, while `5.0 / 2` returns `2.50000`.

4. The add `+` and subtract `-` operators.

    They return the value of the left operand added to/subtracted from the right operand. They're evaluated from left-to-right.

    The operands must be of a numeric type (either int or double).

    These operators return an integer if and only if **both** operands are integer. Otherwise, returns double.

5. The greater than `>` and less than `<` operators.

    They return a boolean indicating whether the left operand is greater/less than the second operand.

    The operands must be of a numeric type (either int or double).

    These operators always return a boolean.

6. The equality `==` operator.

    It returns a boolean indicating whether the left operand is equal to the second operand.

    Both operands must be of numeric types (either int or double), or of boolean types.

    This operator always returns a boolean.

7. The logical and `&&` operator.

    It returns a boolean indicating whether the both of its operands are true or not.

    Both operands must be of boolean types.

    This operator always returns a boolean.

8. The logical or `||` operator.

    It returns a boolean indicating whether one or both of its operands are true or not.

    Both operands must be of boolean types.

    This operator always returns a boolean.

### If statement syntax

The if statement is written as follows:

```
if BOOLEAN_EXPRESSION: STATEMENT_TO_EXECUTE_ON_TRUE
```

The `STATEMENT_TO_EXECUTE_ON_TRUE` is executed if and only if `BOOLEAN_EXPRESSION` evaluates to true.

### Goto statement syntax

the goto statement is used with labels. The label declaration must start with the `label` keyword, followed by a valid label name, followed by a colon, and followed by a statement.

**Note:** Two labels cannot have the same name.
**Note:** The statement **must** be in the same line with the label declaration.

#### Example

To write a program to calculate factorial of 7:

```
N = 7
fact = 1
label re: fact = fact * N
N = N - 1
if N > 1: goto re
```

# Convert String to and from other types

## Convert String to Numeric and other (trivial) types

see: to_readable.cpp

I borrowed the term **readable** from Haskell.

It means as long as there is a `t << stream` operator defined
for the receiving type - aka "readable" - I can take advantage
of the `operator<<`

because read is a stateful business, it's important to look at how to recover
from a failure, using clear() and ignore()

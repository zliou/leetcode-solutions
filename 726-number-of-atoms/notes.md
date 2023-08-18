# Intuition
```
formula := <block>[blocks...]

block := <element>|<group>

group := "("<formula>")"[quantity]

element := <upper case char>[lower case char][quantity]

quantity := <positive integer as a string> 
```

# Approach
* Use a loop to iterate over blocks in the formula
* Check if a block is a group or element based on whether the first char is `(`
* Get the bounds of a group by finding the matching `)` to the opening `(`
* An element will have either one or two alpha chars. The first must be uppercase, and if it has a second, the second must be lowercase
* Get the bounds of a quantity by checking for consecutive numeric chars


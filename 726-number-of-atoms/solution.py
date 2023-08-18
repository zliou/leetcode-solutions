from collections import defaultdict 


"""Given a string and the index of '(', return the index of the matching ')'."""
def find_matching_parenthesis(s: str, open: int) -> int:
    if open >= len(s):
        return -1
    if s[open] != "(":
        return -1
    nested = 0
    for i in range(open + 1, len(s)):
        if s[i] == "(":
            nested += 1
        elif s[i] == ")":
            if nested == 0:
                return i
            nested -= 1
    return -1

"""
Given a string and the last index of a group or atom name,
return a tuple containing the value of the number and the index 
immediately after the number.
"""
def extract_quantity(s: str, close: int) -> tuple:
    i = close + 1
    if i >= len(s) or not s[i].isnumeric():
        return (1, i)

    while i < len(s) and s[i].isnumeric():
        i += 1
    return (int(s[close + 1 : i]), i)

"""
Given a string and the first index of an atom, return tuple(atom: str, next_i: int)
"""
def extract_atom(s: str, start: int) -> tuple:
    if start + 1 <= len(s) and s[start + 1].islower():
        return (s[start : start + 2], start + 2)
    return (s[start : start + 1], start + 1)

"""
Given a dict, string, and starting index, count the atom and return the next index.
"""
def count(counts: defaultdict(int), s: str, start: int) -> int:
    atom, next_i = extract_atom(s, start)
    count = 1
    if next_i < len(s) and s[next_i].isnumeric():
        count, next_i = extract_quantity(s, next_i - 1)
    counts[atom] += count
    return next_i

"""
Given a dict, count the atoms in a given group and return the next index.
"""
def count_group(outer_counts: defaultdict(int), s: str, start: int) -> int:
    nested_counts = defaultdict(int)
    end = find_matching_parenthesis(s, start)
    
    # Loop over group to count the atoms (one atom or group at a time).
    i = start + 1
    while i < len(s) and i < end:
        if s[i] == "(":
            i = count_group(nested_counts, s, i)
            continue
        atom, i = extract_atom(s, i)
        count = 1
        if i < len(s) and s[i].isnumeric():
            count, i = extract_quantity(s, i - 1)
        nested_counts[atom] += count

    group_count, next_i = extract_quantity(s, end)
    for atom in nested_counts:
        outer_counts[atom] += (group_count * nested_counts[atom])
    return next_i

def generate_count_string(counts: defaultdict(int)) -> str:
    atoms = sorted(counts.keys())
    return "".join([atom + str(counts[atom]) if counts[atom] > 1 else atom for atom in atoms])

def count_of_atoms(formula: str) -> str: 
    formula = "(" + formula + ")"
    counts = defaultdict(int)
    _ = count_group(counts, formula, 0)
    return generate_count_string(counts)


class Solution:
    def countOfAtoms(self, formula: str) -> str:
        return count_of_atoms(formula)

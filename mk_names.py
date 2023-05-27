#!/usr/bin/env python3

base_names = [
    'нет войне',
    'ні війні',
]

flag_emoji = '🇺🇦'

def has_case(grapheme):
    return grapheme.isupper() or grapheme.islower()


def slice_alt(s: str):
    alt = []
    non_alt = []
    for ind, char in enumerate(q):
        if char.islower():
            alt.append((ind, char))
        else:
            non_alt.append((ind, char))
    return non_alt, alt



def all_1_caps(s: str):
    l = []
    non, alts = slice_alt(s)
    for alt in alts:
        # print(f'{alt=}')
        l.append(''.join(oo(ch, alt[0]) for ch in enumerate(q)))
    return l

def oo(p, n):
    if p[0] == n:
        return p[1].upper()
    return p[1]

for q in base_names:
    zz = all_1_caps(q)
    print(f'{q=}')
    print(f'{zz=}')

import ast

# comparator function. 
# returns:
# - 0, if indeterminate
# - 1, if right order
# - 2, if wrong order
def compare(first, second):
    # only iterate while we have elements
    size = min(len(first), len(second))
    for i in range(size):
        # compare element-by-element
        e1 = first[i]
        e2 = second[i]
        print(f"comparing: {e1} vs {e2}")
        # int vs int comparison
        # just return the smaller one
        if type(e1) == int and type(e2) == int:
            if e1 == e2:
                continue
            elif e1 < e2:
                return 1
            else:
                return 2
        # list to list comparison
        # recursively compare these elements.
        # if inconclusive, proceed to the next elements of first and second
        elif type(e1) == list and type(e2) == list:
            res = compare(e1, e2)
            if res == 0:
                continue
            else:
                return res
        # int to list comparison
        # wrap the int in a list and recursively compare.
        # if inconclusive, proceed to the next elements of first and second
        else:
            if type(e1) == int:
                res = compare([e1], e2)
                if res == 0:
                    continue
                else:
                    return res
            else:
                res = compare(e1, [e2])
                if res == 0:
                    continue
                else:
                    return res
    
    # element-wise comparisons were inconclusive,
    # so we determine the ordering by length of remaining elements
    if len(first) == len(second):
        return 0
    elif len(first) < len(second):
        return 1
    else:
        return 2
        
# forgive me, i'm using python JUST for this question
# i wasn't about to write a list parser,,, especially not in c++,,,
def main():
    with open("input", "r") as f:
        current = 0
        sum = 0
        index = 1
        
        line = f.readline()
        while line != '':
            line = line.strip()

            # read 3 lines at a time: first, second, and a new line
            if current == 0:
                first = ast.literal_eval(line)
            elif current == 1:
                second = ast.literal_eval(line)
            elif current == 2:
                print(f"=== pair {index} ===")
                cmpres = compare(first, second)
                print(f"verdict: {cmpres}")
                # add index to sum if this pair is in the right order
                if cmpres == 1:
                    print(f"adding: {index}")
                    sum += index
                index += 1
                print("")
            
            current = (current + 1) % 3
            line = f.readline()
            
        print(sum)

if __name__ == "__main__":
    main()

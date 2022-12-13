import ast
import functools

# we can modify the return values of this  function 
# to make it a proper comparator function. 
# returns:
# - 0, if indeterminate
# - -1, if right order
# - 1, if wrong order
def compare(first, second):
    size = min(len(first), len(second))
    for i in range(size):
        e1 = first[i]
        e2 = second[i]
        if type(e1) == int and type(e2) == int:
            if e1 == e2:
                continue
            elif e1 < e2:
                return -1
            else:
                return 1
        elif type(e1) == list and type(e2) == list:
            res = compare(e1, e2)
            if res == 0:
                continue
            else:
                return res
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
    
    if len(first) == len(second):
        return 0
    elif len(first) < len(second):
        return -1
    else:
        return 1
        
def main():
    with open("input", "r") as f:
        # read all the packets, including the divider packets
        packets = [ast.literal_eval(line.strip()) for line in f.readlines() if line != '\n']
        packets += [[[2]], [[6]]]
        
        # sort the packets in order
        # we can use functools.cmp_to_key to convert our comparator
        # function to a key function for sorted()
        sorted_packets = sorted(packets, key=functools.cmp_to_key(compare))
        
        # find the decoder key by searching for the divider packets
        key = (sorted_packets.index([[2]]) + 1) * (sorted_packets.index([[6]]) + 1)
        print(key)

if __name__ == "__main__":
    main()

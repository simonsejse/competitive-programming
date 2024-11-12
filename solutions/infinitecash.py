s = int(input(), base=2)
d = int(input(), base=2)
m = int(input(), base=2)
cnt = 0
initial_m = m
previous_m = m

while (m > 0):
    if m >= initial_m and cnt != 0: 
        # maype equal
        print("Infinite money!")
        exit(0)
        break
    
    m = m >> 1

    cnt += 1

    if cnt % d == 0:
        m += s
        if (previous_m == m):
            print("Infinite money!")
            exit(0)
            break
        previous_m = m
ret = f'{cnt:#b}'
ret = ret.replace('0b', '')

print(f'{ret}')

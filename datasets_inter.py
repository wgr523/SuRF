
words = open("words.txt")
words_small = open("words_small.txt", "w")
words_large = open("words_large.txt","w")
# perform file operations
i = 0
num_lines = sum(1 for line in open('words.txt'))
for line in words:
    if i % 100 == 0 and line.find("y"):
        words_small.write(line)
    elif i % 100 == 1 and line.find("y"):
        words_large.write(line)
    i+=1
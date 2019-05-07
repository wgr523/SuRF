with open('words/words.txt') as fin:
    file_cnt=0
    line_cnt=0
    l0=[]
    l1=[]
    l2=[]
    for line in fin:
        if line_cnt%70000==0 and line_cnt>0:
            fout0 = open('words/eval_{}_0.txt'.format(file_cnt),'w')
            fout1 = open('words/eval_{}_1.txt'.format(file_cnt),'w')
            fout2 = open('words/eval_{}_2.txt'.format(file_cnt),'w')
            file_cnt+=1
            for line in sorted(l0):
                fout0.write(line)
            for line in sorted(l1):
                fout1.write(line)
            for line in sorted(l2):
                fout2.write(line)
            l0=[]
            l1=[]
            l2=[]
            fout0.close()
            fout1.close()
            fout2.close()
        if line_cnt%70000<50000:
            l0.append(line)
        elif line_cnt%70000<60000:
            l1.append(line)
        else:
            l2.append(line)
        line_cnt+=1

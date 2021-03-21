#  author: air029
from matplotlib import pyplot as plt

# parameter
filename = 'C:/Users/mjh12/nohup.out'
data = 'Netflix'
topk = 100
RETRIEVEK = 17770
K = [64, 128, 256, 512]
K_ROUND = 4



type = -1
k_round = -1

# init
retrieve_l = [[] for j in range(K_ROUND)]
recall_l = [[] for j in range(K_ROUND)]
retrieve_c = [[] for j in range(K_ROUND)]
recall_c = [[] for j in range(K_ROUND)]
retrieve_h = [[] for j in range(K_ROUND)]
recall_h = [[] for j in range(K_ROUND)]

# read
with open(filename, 'r') as f:
    for line in f:
        if 'L' == line[0]:
            type = 1
            k_round = -1
        elif 'C' == line[0]:
            type = 2
            k_round = -1
        elif 'H' == line[0]:
            type = 3
            k_round = -1

        if 1 == type:
            if 'K' == line[0]:
                k_round = k_round + 1
                #print(k_round)
                #print(K[k_round])
            elif 'r' == line[0]:
                word1 = line.split(':')
                word2 = word1[1].split(' ')
                word4 = word2[1].split('\t')
                word3 = word1[2].split('\n')
                num1 = int(word4[0])
                num2 = float(word3[0])
                retrieve_l[k_round].append(num1)
                recall_l[k_round].append(num2)
        if 2 == type:
            if 'K' == line[0]:
                k_round = k_round + 1
            elif 'r' == line[0]:
                word1 = line.split(':')
                word2 = word1[1].split(' ')
                word4 = word2[1].split('\t')
                word3 = word1[2].split('\n')
                num1 = int(word4[0])
                num2 = float(word3[0])
                retrieve_c[k_round].append(num1)
                recall_c[k_round].append(num2)
        if 3 == type:
            if 'K' == line[0]:
                k_round = k_round + 1
            elif 'r' == line[0]:
                word1 = line.split(':')
                word2 = word1[1].split(' ')
                word4 = word2[1].split('\t')
                word3 = word1[2].split('\n')
                num1 = int(word4[0])
                num2 = float(word3[0])
                retrieve_h[k_round].append(num1)
                recall_h[k_round].append(num2)
"""
# plot
plt.figure('Recall Retrieved_item Curve of ' + data + ' TOP' + str(topk))


plt.subplot(1, 3, 1)
plt.title('L2')
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
for i in range(K_ROUND):
    plt.plot(retrieve_l[i], recall_l[i], label='K='+str(K[i]))
plt.legend()

plt.subplot(1, 3, 2)
plt.title('Cosine')
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
for i in range(K_ROUND):
    plt.plot(retrieve_c[i], recall_c[i], label='K='+str(K[i]))
plt.legend()

plt.subplot(1, 3, 3)
plt.title('H2')
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
for i in range(K_ROUND):
    plt.plot(retrieve_h[i], recall_h[i], label='K='+str(K[i]))
plt.legend()

plt.show()

"""

# plot
plt.figure('Recall Retrieved_item Curve of ' + data + ' TOP' + str(topk))

plt.subplot(1, 4, 1)
K = 64
i = 0
plt.title('K=' + str(K))
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
plt.plot(retrieve_h[i], recall_h[i], label='H2_K='+ str(K))
plt.plot(retrieve_l[i], recall_l[i], label='L2_K='+ str(K))
plt.plot(retrieve_c[i], recall_c[i], label='Sign_K='+ str(K))
plt.legend()

plt.subplot(1, 4, 2)
K = 128
i = 1
plt.title('K=' + str(K))
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
plt.plot(retrieve_h[i], recall_h[i], label='H2_K='+ str(K))
plt.plot(retrieve_l[i], recall_l[i], label='L2_K='+ str(K))
plt.plot(retrieve_c[i], recall_c[i], label='Sign_K='+ str(K))
plt.legend()

plt.subplot(1, 4, 3)
K = 256
i = 2
plt.title('K=' + str(K))
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
plt.plot(retrieve_h[i], recall_h[i], label='H2_K='+ str(K))
plt.plot(retrieve_l[i], recall_l[i], label='L2_K='+ str(K))
plt.plot(retrieve_c[i], recall_c[i], label='Sign_K='+ str(K))
plt.legend()

plt.subplot(1, 4, 4)
K = 512
i = 3
plt.title('K=' + str(K))
plt.xlabel('Retrieved_item')
plt.ylabel('Recall')
plt.grid(linestyle='-.')
plt.plot(retrieve_h[i], recall_h[i], label='H2_K='+ str(K))
plt.plot(retrieve_l[i], recall_l[i], label='L2_K='+ str(K))
plt.plot(retrieve_c[i], recall_c[i], label='Sign_K='+ str(K))
plt.legend()

plt.show()
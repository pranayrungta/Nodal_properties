filename = 'btc_RSFsampleSmall.txt'

data = open(filename,'r').read()

data = data.replace('],','],\n')

f = open(filename,'w')
f.write(str(data))
f.close()

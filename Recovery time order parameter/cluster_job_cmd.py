criteria = [  '.cpp']
nonCriteria  = [ '$' ]



import os
ls = os.listdir('./')
files = [ filename for filename in ls if( all(name in filename for name in criteria)
                                          and not
                                          all(name in filename for name in nonCriteria)) ]
job_file = 'cmds.txt'
f= open(job_file, 'w')
f.write('echo \n')
f.write('echo "Submitting jobs..."\n')
f.write('echo \n\n')
for c,filename in enumerate(files):
    f.write('echo "Compiling Program %s : %s " \n'%((c+1),filename) )
    f.write('g++ -std=c++11 %s -o %s.run \n'%(filename, filename[:-4]) )
    f.write('qsub -o %s.out -e %s.out -V -b y -cwd ./%s.run  \n'%(filename[:-4],filename[:-4],filename[:-4]) )
    f.write('echo " " \n' )
    f.write('\n')

f.write('\n')
f.write('echo\n')
f.write('echo "Done!!!" \n')
f.write('echo\n')
f.close()

def make_executable(path):
    mode = os.stat(path).st_mode
    mode |= (mode & 0o444) >> 2    # copy R bits to X
    os.chmod(path, mode)

make_executable(job_file)

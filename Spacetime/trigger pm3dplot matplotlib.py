criteria = ['.spt','']

title = 'auto' # 'None'  'auto'  'TITLE'

xlabel = ( 'time', {'fontsize':20} )#( 'time', {'fontsize':20} )
ylabel = ( r'$\langle x \rangle$', {'fontsize':25} ) #( r'$\langle x \rangle$', {'fontsize':25} ) 

xlim={} #{'xmin':1, 'xmax':50}
ylim={} #{'ymin':1, 'ymax':50}

colorRange =  dict(vmin=-1.5, vmax=1.5)# dict(vmin=0, vmax=1)

vertical_on_x = True # False  True
figsize = (10,6)

output = 'png' # 'show' 'png' 'pdf' 'eps'





import sys
sys.dont_write_bytecode = True
from Pranay.matplotlib.matplotlibpm3d import *

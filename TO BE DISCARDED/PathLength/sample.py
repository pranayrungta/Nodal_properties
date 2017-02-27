def avgDegree(connections):
    avg=0
    for i in connections.values():
        avg += len(i)
    avg/= ( 1.0*len(connections) )
    return avg


def sw_result(netProperty):
    result={}
    ic={}
    for args, connections in data:
        if(not result.has_key(args['n'])):
            result[ args['n'] ]={}
            ic[ args['n'] ]={}
        if(not result[ args['n'] ].has_key(args['k'])):
            result[ args['n'] ][ args['k'] ]={}
            ic[ args['n'] ][ args['k'] ]={}
        if(not result[ args['n'] ][ args['k'] ].has_key(args['p'])):
            result[ args['n'] ][ args['k'] ][ args['p'] ]=0.0
            ic[ args['n'] ][ args['k'] ][ args['p'] ]=0

        result[ args['n'] ][ args['k'] ][ args['p'] ]+=netProperty(connections)
        ic[ args['n'] ][ args['k'] ][ args['p'] ]+=1
    for n,kp in result.iteritems():
        for k,pv in kp.iteritems():
            for p in pv.iterkeys():
                result[n][k][p] /= ic[n][k][p]
    return result

def rsf_result(data,netProperty):
    result={}
    ic={}
    for r, connections in data:
        if(not result.has_key(r['n'])):
            result[ r['n'] ]={}
            ic[ r['n'] ]={}
        if(not result[ r['n'] ].has_key(r['k'])):
            result[ r['n'] ][ r['k'] ]=0
            ic[ r['n'] ][ r['k'] ]=0

        result[ r['n'] ][ r['k'] ]+=netProperty(connections)
        ic[ r['n'] ][ r['k'] ]+=1
    for n,kv in result.iteritems():
        for k in kv.iterkeys():
            result[n][k] /= ic[n][k]
    return result

def dsf_result(netProperty):
    result={}
    for args, connections in data:
        result[ args['order'] ]=netProperty(connections)
    return result

def star_result(netProperty):
    result={}
    for r, connections in data:
        result[ r['n'] ]=netProperty(connections)
    return result

def ring_result(netProperty):
    result={}
    for arg, connections in data:
        if(   not result.has_key( arg['n'] )   ):
            result[ arg['n'] ]={}
        result[ arg['n'] ][ arg['k'] ]=netProperty(connections)
    return result




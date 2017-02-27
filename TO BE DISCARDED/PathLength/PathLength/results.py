def sw_result(data,netProperty):
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
        print '\r',args,
    for n,kp in result.iteritems():
        for k,pv in kp.iteritems():
            for p in pv.iterkeys():
                result[n][k][p] /= ic[n][k][p]
    return result


def rsf_result(data,netProperty):
    result={}
    ic={}
    for args, connections in data:
        if(not result.has_key(args['n'])):
            result[ args['n'] ]={}
            ic[ args['n'] ]={}
        if(not result[ args['n'] ].has_key(args['k'])):
            result[ args['n'] ][ args['k'] ]=0
            ic[ args['n'] ][ args['k'] ]=0

        result[ args['n'] ][ args['k'] ]+=netProperty(connections)
        ic[ args['n'] ][ args['k'] ]+=1
        print '\r',args,
    for n,kv in result.iteritems():
        for k in kv.iterkeys():
            result[n][k] /= ic[n][k]
    return result


def dsf_result(data,netProperty):
    result={}
    for args, connections in data:
        result[ args['order'] ]=netProperty(connections)
    return result


def star_result(data,netProperty):
    result={}
    for args, connections in data:
        result[ args['n'] ]=netProperty(connections)
    return result

def ring_result(data,netProperty):
    result={}
    for args, connections in data:
        if(   not result.has_key( args['n'] )   ):
            result[ args['n'] ]={}
        result[ args['n'] ][ args['k'] ]=netProperty(connections)
    return result

#!python

import os
import eol_scons

def NC_utils(env):
    env.Require(['prefixoptions'])
    env.Append(LIBPATH=[env['OPT_PREFIX']+'/vardb'])
    env.Append(LIBPATH=[env['OPT_PREFIX']+'/vardb/raf'])

env = Environment(GLOBAL_TOOLS = [NC_utils])

if env['INSTALL_PREFIX'] == '#':
    SConscript('vardb/SConscript')
    SConscript('vardb/raf/SConscript')

SConscript('asc2cdf/SConscript')
#subdirs = Split("""
#	asc2cdf
#""")

#for subdir in subdirs:
#    SConscript(os.path.join(subdir, '/SConscript'))

#asc2cdf_HRT/
#ascav/
#flt_time/
#g2n/
#gndproc/
#mkcdf/
#n2asc/
#n2aTest/
#nc2asc/
#nc2iwg1/
#ncav/
#nc_compare/
#nc_dips/
#ncextr/
#ncfillvar/
#nc_gap/
#ncmerge/
#ncReorder/
#nc_sane/
#ncstat/
#ncvarlist/
#repair/
#skel/

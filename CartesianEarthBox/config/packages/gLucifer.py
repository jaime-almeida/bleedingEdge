import os
from config import Package
from StgDomain import StgDomain

class gLucifer(Package):

    def setup_dependencies(self):
        self.stgdomain = self.add_dependency(StgDomain, required=True)

    def gen_locations(self):
        yield ('/usr', [], [])
        yield ('/usr/local', [], [])

    def gen_envs(self, loc):
        for env in Package.gen_envs(self, loc):
            self.headers = [os.path.join('StGermain', 'StGermain.h'),
                            os.path.join('StgDomain', 'StgDomain.h'),
                            os.path.join('gLucifer', 'gLucifer.h'),
            if self.find_libraries(loc[2], 'gLucifer'):
                env.PrependUnique(LIBS=['gLucifer'])
                yield env

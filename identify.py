#!/usr/bin/env python

import os
import re

# Detect hg repositories starting from the root '.' directory.
def retrieve_repos():
    repos = {}
    paths = ['.']
    while paths:
        path = paths.pop()
        if os.path.realpath(path) in repos:
            continue
        for root, dirs, files in os.walk(path):
            hgdirs = dirs[:]
            for d in hgdirs:
                if d == '.hg':
                    repos[os.path.realpath(root)] = root
                else:
                    p = os.path.join(root, d)
                    if os.path.islink(p) and os.path.abspath(p) not in repos:                            
                        paths.append(p) 
    repos = repos.values()
    repos.sort()
    return repos

# Identify each repository detected and display information.
def identify_repos():
    try:
        from mercurial import commands, error, hg, ui, util, node
    except ImportError:
        print 'Mercurial not found, not identifying.'
        pass
    else:
        localui = ui.ui()
        counter = 1
        for r in retrieve_repos():
            try:
                repo = hg.repository(localui, r)
            except RepoError:
                print 'Repository not found, not identifying.'
                pass
            else:
                localui = repo.ui
                try:
                    ctx = repo[None]
                except TypeError:
                    ctx = repo.workingctx()
                parents = ctx.parents()
                revision = [node.hex(parents[0].node())][0]
                localui.pushbuffer()
                commands.paths(localui, repo)
                path = localui.popbuffer()
                path = re.sub("http[s]?://[a-zA-Z]*:[a-zA-Z]*\**@","https://", path)
                print '[tree%d]' % counter
                print 'root = %s' % r.replace('./','')
                print 'revision = %s' % revision
                print 'path.%s' % path
                counter += 1

if __name__ == "__main__":
    identify_repos()


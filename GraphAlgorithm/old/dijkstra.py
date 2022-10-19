#-*- coding: utf-8 -*-

#!/usr/bin/python
#coding: utf-8

import sys

INF = 1000000.0

dist = []
data = open("data.txt", "r").read().split()

dic = {'city': data[0].split(',')}
cityNum = len(data[0].split(','))
for i in range(1, 1 + cityNum):
    dist.append(data[i].split(','))

dic['distance'] = dist
def ShortestPath(G):
    # initialize
    check = []
    distance = []
    path = []
    for i in range(0, cityNum):
        check.append(False)
        distance.append(G['distance'][i])
        path.append([])

    P = {'city': G['city']}
    P['shortest paths'] = {'distance': G['distance']}
    P['shortest paths']['paths'] = path[:]
    
    for src in range(0, cityNum):
        for i in range(0, cityNum):
            check[i] = False
            path[i] = []
            if src == i:
                path[i].append(P['city'][i])
            if float(distance[src][i]) > 0.0 and float(distance[src][i]) < 1000000.0:
                path[i].append(P['city'][src])
                path[i].append(P['city'][i])

        for i in range(src, cityNum):
            min = INF
            for j in range(0, cityNum):
                if not check[j] and float(distance[src][j]) < min:
                    min = float(distance[src][j])
                    pos = j
            check[pos] = True

            for j in range(0, cityNum):
                if not check[j] and float(distance[src][j]) > float(distance[src][pos]) + float(distance[pos][j]):
                    distance[src][j] = float(distance[src][pos]) + float(distance[pos][j])
                    path[j] = path[pos][:]
                    path[j].append(P['city'][j])
        
        P['shortest paths']['paths'][src] = path[:]

    for i in range(0, cityNum):
        for j in range(0, cityNum):
            P['shortest paths']['distance'][i][j] = float(P['shortest paths']['distance'][i][j])
            if len(P['shortest paths']['paths'][i][j]) == 0:
                P['shortest paths']['paths'][i][j].append( None)
    P['shortest paths']['distance'] = distance[:]
    return P

P = ShortestPath(dic)
print("P = ", end = '')
print(P)

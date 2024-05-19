checkfile = open('Chennai_rest_addrss.txt', 'r+', encoding='utf-8')
ogfile = open('city_wise_rests/zomato_chennai.txt', 'r+', encoding='utf-8')

lkeep = {}
lc=0
for line in checkfile.readlines():
    lc+=1
    if line.startswith("ADDRESS NOT FOUND"):
        continue
    lkeep[lc] = line

final = []
for k,v in lkeep.items():
    final.append(v)

checkfile.seek(0)
checkfile.writelines(final)
checkfile.close

lchange=[]
lc=0
for line in ogfile.readlines():
    lc+=1
    if lc not in lkeep:
        continue
    ch_line = line[:line.rfind(':')+2]+lkeep[lc]
    print(ch_line)
    lchange.append(ch_line)

ogfile.seek(0)
ogfile.writelines(lchange)
ogfile.close()
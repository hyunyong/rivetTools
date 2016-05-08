import os

def reader(file_name):
  in_f = open(file_name)
  out_f = open(file_name.replace(".lhe", "_skim.lhe"),"w")
  on = False
  for x in in_f:
     if x.startswith("<event>"):     
       tmps = ""
       count = 0
       count += 1
       on = True
     if x.startswith("</event>"):
       on = False
       if count == 10:
         out_f.write(tmps)
     if on:
       tmps += x
       count += 1
     if not on:
       out_f.write(x)
  out_f.close()



f_list = [x for x in os.listdir(".") if x.endswith(".lhe")]

for x in f_list:
  reader(x)



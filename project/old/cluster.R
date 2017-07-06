library(flexclust)
library(cluster)

m<-read.table("~/Documents/project/results.csv", quote="\"", comment.char = "")
names(m) <- c("x","y","z")
mpg=m[,2]
wt=m[,1]
plot(wt, mpg, main="Clustering", xlab="Length ", ylab="Clearance ", pch=19) 
l=pam(m[,1:3], 3)$medoids
points(pam(m[,1:3], 3)$medoids, pch = 1, col = "red")

kcca.out1_1 <- kcca(m[,1:3], k=3, family=kccaFamily("kmedians"), save.data=TRUE)
clusters(kcca.out1_1)
#hist(clusters(kcca.out1_1))

a=which(m[,1]==l[1,1]&m[,2]==l[1,2]&m[,3]==l[1,3])
b=which(m[,1]==l[2,1]&m[,2]==l[2,2]&m[,3]==l[2,3])
c=which(m[,1]==l[3,1]&m[,2]==l[3,2]&m[,3]==l[3,3])
d=which.max( m[,1] )
e=which.max( m[,2] )
f=which.max( m[,3] )

from<-paste("~/Documents/p5js/Exp1/public/paths/path",a[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path0.json", overwrite = TRUE)
from<-paste("~/Documents/p5js/Exp1/public/paths/path",b[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path1.json", overwrite = TRUE)
from<-paste("~/Documents/p5js/Exp1/public/paths/path",c[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path2.json", overwrite = TRUE)
from<-paste("~/Documents/p5js/Exp1/public/paths/path",d[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path3.json", overwrite = TRUE)
from<-paste("~/Documents/p5js/Exp1/public/paths/path",e[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path4.json", overwrite = TRUE)
from<-paste("~/Documents/p5js/Exp1/public/paths/path",f[1]-1, ".json", sep="")
file.copy(from, "~/Documents/p5js/Exp1/public/paths/final/path5.json", overwrite = TRUE)



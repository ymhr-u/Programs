t_fun <- function(da1,da2,fn,name){
ans1 <- t.test(da1,da2,var=T)
ans2 <- t.test(da1,da2,var=F)
ans3 <- wilcox.test(da1,da2)
ave1 = ave(da1)[1]
sd1 = sd(da1)
ave2 = ave(da2)[1]
sd2 = sd(da2)
dif = abs(ave1 - ave2)
result <- c(name,ave1,sd1,ave2,sd2,dif,ans1$statistic,ans1$p.value,ans2$statistic,ans2$p.value,ans3$statistic,ans3$p.value)
names(result) = c("m/z名","平均1","標準誤差1","平均2","標準誤差2","平均の差","等分散t","等分散p","不等分散t","不等分散p","ウィルコクソンW","ウィルコクソンp")
write.table(t(result),fn,append=T,quote=F,sep=",",row.names=F,col.names=T,fileEncoding="CP932")
write.table("",fn,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
}
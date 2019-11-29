chi_test2 <- function(dat,filename) 
{
ans = chisq.test(table(dat))
x2 = ans$statistic
dof = ans$parameter
p_value = ans$p.value
ex = ans$expected
res = ans$residuals
std = ans$stdres
name = paste(colnames(dat)[1],"(行) vs",colnames(dat)[2],"(列)")
result = cbind(x2,dof,p_value,rownames(table(dat)),table(dat),ex,res,std)
result[2:nrow(result),c(1:3)] = ""
rownames(result)[1:nrow(result)] = ""
write.table(matrix(c(name,colnames(result)),nrow=1),filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
write.table(result,filename,append=T,quote=F,sep=",",row.names=T,col.names=F,fileEncoding="CP932")
write.table("",filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
}
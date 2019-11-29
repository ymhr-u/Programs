reg_fun <- function(dat,filename,response)
{

ans <- lm(dat$Y~.,data=dat)
s.ans=summary(ans)
coe <- s.ans$coef
CI.low <- coe[,1]-1.96*coe[,2]
CI.up <- coe[,1]+1.96*coe[,2]
aic <- AIC(ans)
R.squared = s.ans$r.squared
Adj.R.squared = s.ans$adj.r.squared
N <- nrow(dat)
result <- cbind(coe,CI.low,CI.up,aic,R.squared,Adj.R.squared,N)
result[2:nrow(result),c(7:10)]=""
res <- paste("Y = ",response)
write.table(res,filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
write.table(matrix(c("",colnames(result)),nrow=1),filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
write.table(result,filename,append=T,quote=F,sep=",",row.names=T,col.names=F,fileEncoding="CP932")
write.table("",filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")

}


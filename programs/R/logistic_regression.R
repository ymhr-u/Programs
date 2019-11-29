logi_fun <- function(data,file,disease)
{
ans <- glm(data$Y~.,data=data,family=binomial)
s.ans <- summary(ans)
coe <- s.ans$coefficient
RR <- exp(coe[,1])
RRlow <- exp(coe[,1]-1.96*coe[,2])
RRup <- exp(coe[,1]+1.96*coe[,2])
N <- nrow(data)
aic <- AIC(ans)
result <- cbind(coe,RR,RRlow,RRup,aic,N)
colnames(result)[6:7] <- c("RR95%CI.low","RR95%CI.up")
if(nrow(result)>=2){result[2:nrow(result),8:9] <- ""}

write.table(disease,file,append=T,quote=F,sep=",",row.names=F,col.names=F)
write.table(matrix(c("",colnames(result)),nrow=1),file,append=T,quote=F,sep=",",row.names=F,col.names=F)
write.table(result,file,append=T,quote=F,sep=",",row.names=T,col.names=F)
write.table("",file,append=T,quote=F,sep=",",row.names=F,col.names=F)
}
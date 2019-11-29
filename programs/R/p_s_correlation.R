cor_fun <-function(dat,filename) #引数は（解析用データ,出力先ファイル名)
{

for(i in 2:ncol(dat))
{
ans_c = cor.test(dat[,1],dat[,i])
c= ans_c$estimate #ピアソンの相関係数
c_p= ans_c$p.value #そのp値
ans_s = cor.test(dat[,1],dat[,i],method="s")
s= ans_s$estimate #スピアマンの相関係数
s_p= ans_s$p.value #そのp値
result = c(paste(colnames(dat)[1],"VS",colnames(dat)[i]),c,c_p,s,s_p)
names(result)[1] = "Name"
names(result)[3] = "ピアソンの相関係数のp値"
names(result)[5] = "スピアマンの相関係数のp値"
if(i == 2){
write.table(matrix(c(colnames(t(result))),nrow=1),filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
}
write.table(t(result),filename,append=T,quote=F,sep=",",row.names=F,col.names=F,fileEncoding="CP932")
}

}
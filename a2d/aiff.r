framerate = 44100
dir = "/Users/lolife/Documents/"
files = c( "piano.aif.txt" )

ts = array()
ps = array()
names = array()
count = 1
file_num = 1
#for( f in files) {
	f = files[1]
	filename = paste0( dir, f)
	dt = read.table(filename)
	d = data.frame( n=dt$V1, a=dt$V2 )
	t = fft(d$a)
#	p = Re( t * Conj(t) )
	p = Re( t )
	n = (p-mean(p))/sd(p)
	s = seq(0,(length(d$n)/2)-1,by=1)
	f = data.frame( t=s*framerate/length(d$n), p=n[0:(length(n)/2)])
	#plot(d,type="l")
	#print( which(f$p > 1) )
	r=rank(f$p)
	for( n in seq(0,1000,by=1)) {
		ind = which(r == max(r)-n)
		names[count]=file_num
		ts[count]=f$t[ind]
		ps[count]=f$p[ind]
		count = count + 1
	}
	file_num = file_num+1
#}
freqs = data.frame(n=names,t=ts,p=ps)
print(freqs)

s = seq(1,length(d$n),by=1)
as = function(x){32768/4*sin(2*pi*x*s/44100)}
total = 0
i=1
for( v in freqs$t) {total = total + (freqs$p[i]*as(v));i=i+1}
sc = data.frame( t=c(min(total),max(total)),a=c((-2**16/2)+1,(2**16/2)-1))
sc.fit = lm( sc$a ~ sc$t )
newt = (total*sc.fit$coef[2])+sc.fit$coef[1]
write(round(newt,0),file="pno_1000sin.txt",sep="\n")

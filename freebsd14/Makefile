SUBDIR= kmod client

all:
.for dir in ${SUBDIR}
	${MAKE} -C ${dir}
.endfor

clean:
.for dir in ${SUBDIR}
	${MAKE} -C ${dir} clean
.endfor
	find . -name ".depend*" -delete

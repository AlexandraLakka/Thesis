FROM public.ecr.aws/lambda/python:3.8

COPY merge.py ${LAMBDA_TASK_ROOT}

RUN pip3 install algorithms
#RUN pip3 install numpy

CMD ["merge.handler"]

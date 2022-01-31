FROM public.ecr.aws/lambda/python:3.8

COPY quick.py ${LAMBDA_TASK_ROOT}

RUN pip3 install algorithms 
CMD [ "quick.handler" ]

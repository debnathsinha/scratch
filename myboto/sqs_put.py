import simplejson, boto, uuid
sqs = boto.connect_sqs()
q = sqs.create_queue('my_msg_pump')
q.write(q.new_message(body=simplejson.dumps(['foo'])))

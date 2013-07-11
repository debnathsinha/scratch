import boto
s3 = boto.connect_s3()
key = s3.get_bucket('media.yourdomain.com').get_key('examples/s3.py')
key.get_contents_to_filename('myfile.py')

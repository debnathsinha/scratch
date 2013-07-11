import boto
s3 = boto.connect_s3()
bucket = s3.create_bucket('media.yourdomain.com')
key = bucket.new_key('examples/s3.py')
key.set_contents_from_filename('/Users/dsinha/code/myboto/s3.py')
key.set_acl('public-read')

(ns foo.core
	(:require [clj-http.client :as client]))

(defn foo
  "I don't do a whole lot."
  [x]
  (println x "Hello, World!"))

(defn -main
	"Prints the first 50 characters of yelp.com"
	[& args]
	(println (apply str
		(take 50
			(:body (client/get "http://www.yelp.com"))))))

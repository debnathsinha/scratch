(use 'ring.adapter.jetty)
(require adder.core)

(run-jetty #'adder.core/app {:port 8080})
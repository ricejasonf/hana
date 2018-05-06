.PHONY:image dev image_doc doc

image:
	docker build --rm -t hana_build .

dev:
	docker run --rm -it -p 8080:8080 -v ${shell pwd}:/opt/src:ro hana_build

TEMPLATE = subdirs
SUBDIRS = src

packagesExist(gstreamer-0.10 gstreamer-app-0.10): SUBDIRS += gstvideothumbnailer
else: warning("gstreamer packages not available, video thumbnailing disabled")

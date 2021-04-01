About
======

The aim of this project was to develop a universal approach to very ambitious problem of restoring of the 3D shape of some object having only its snapshots.  

This is a very old and well-know problem in Computer Graphics and Computational Geometry [1,2]. The standard approach implies direct restoration of positions of L2-close points using geometric calculations. This approach is not stable and rarely gives good results.

There is a different, more original approach though. For example similar to that described in [3] using variational optimization solver to reconstruct a free-form, texture-mapped, 3D scene models from a single painting or photograph

Idea
====

My approach to the problem was quite straightforward. 
First of all I noticed that the snapshots of 3d object are just projections of this object to some 2d plane. 
As a result one can use epipolar geometry to determine the approximate position of points in 3d space [3].  

Development
===========

I created the very first implementation of this idea in 2004 in C++ as a PoC, it was not optimal in terms of computational efficiency and worked with satisfactory results only on small set of images. Surprisingly the binary for Windows is still executable (I checked on the latest Windows 10) – see the compiled application in src/RELEASE/Image.exe

In folder slides/ one can find the two original 2d snapshots of 3d object – in this case this is  just a stereo pair: snapshot_left_eye and snapshot_right_eye. The size of images must be the same, only bmp format is supported.

The resulting image is saved to restored_image_avr.png.


References
=========
[1] O. Faugeras, L. Robert What can two images tell us about a third one? July 1993

[2] 3D reconstruction (https://en.wikipedia.org/wiki/3D_reconstruction_from_multiple_images)

[3] Epipolar geometry (https://en.wikipedia.org/wiki/Epipolar_geometry)

[3]  L. Zhang, G. Dugas-Phocion, J.-S. Samson, and S. M. Seitz,  Single view modeling of free-form scenes, Journal of Visualization and Computer Animation, 2002, vol. 13, no. 4, pp. 225-235.  (https://grail.cs.washington.edu/projects/svm/jvca2002.pdf ) 

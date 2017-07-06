l1=0.08;
l2=0.08;
a=6;
b=3;
c=1;
clearance=imread('clearance.jpg');
voronoi=imread('voronoi.jpg' );
voronoi=~voronoi;

wl=exp(-((double(clearance)-10).^2)/2*(l1^2));
wx=exp(-((double(clearance)-25).^2)/2*(l2^2));
w=((((1+wl).^a).*((1+wx).^b).*((1+voronoi).^c)));
normw = w - min(w(:));
normw=uint8(normw);
imwrite(normw,'prob.jpg');
package edu.uga.clubs.test;

import java.sql.Connection;
import java.util.Date;

import edu.uga.clubs.ClubsException;
import edu.uga.clubs.model.Club;
import edu.uga.clubs.model.Membership;
import edu.uga.clubs.model.ObjectModel;
import edu.uga.clubs.model.Person;
import edu.uga.clubs.model.impl.ObjectModelImpl;
import edu.uga.clubs.persistence.Persistence;
import edu.uga.clubs.persistence.impl.DbUtils;
import edu.uga.clubs.persistence.impl.PersistenceImpl;


// This is a simple class to test the creation of the entity classes
// and associations in the Clubs example.
//
public class ObjectModelCreate
{
    public static void main(String[] args)
    {
         Connection conn = null;
         ObjectModel objectModel = null;
         Persistence persistence = null;
         
         Club        bridge;
         Club        chess;
         Club        tennis;
         Club        running;
         Person      joe;
         Person      mary;
         Person      bob;
         Person      julie;
         Person      heather;
         Membership  membership;
         
         // get a database connection
         try {
             conn = DbUtils.connect();
         } 
         catch (Exception seq) {
             System.err.println( "ObjectModelDelete: Unable to obtain a database connection" );
         }
         
         // obtain a reference to the ObjectModel module      
         objectModel = new ObjectModelImpl();
         // obtain a reference to Persistence module and connect it to the ObjectModel        
         persistence = new PersistenceImpl( conn, objectModel ); 
         // connect the ObjectModel module to the Persistence module
         objectModel.setPersistence( persistence );   

         try {
             
             // create a few people
             joe = objectModel.createPerson( "joe", "joepass", "joe@mail.com", "Joe", "Doe", 
					     "133 Maple St., Big Town, AZ. 87888", "333-4456" );
             objectModel.storePerson( joe );

             mary = objectModel.createPerson( "mary", "marypass", "mary@mail.com", "Mary", "Swift", 
					      "14 Oak Dr., Small Town, TX. 77888", "444-9876" );
             objectModel.storePerson( mary );

             bob = objectModel.createPerson( "bob", "bobpass", "bob@mail.com", "Robert", "Wilson", 
					     "33 Cedar Cr., Middle Town, NV. 81888", "567-7788" );
	     objectModel.storePerson( bob );

             julie = objectModel.createPerson( "julie", "juliepass", "julie@mail.com", "Julie", "Hart", 
					       "99 Magnolia St., Splash Town, NY. 21888", "364-7592" );
	     objectModel.storePerson( julie );

             heather = objectModel.createPerson( "heather", "heatherpass", "julie@mail.com", "Heather", "Brooks", 
						 "1 Pine Ave., Boom Town, GA. 30688", "339-9923" );
	     objectModel.storePerson( heather );
             

             bridge = objectModel.createClub( "Bridge", "33 Leaf St., Blossom, OR. 88888", new Date(), joe );
	     objectModel.storeClub( bridge );
             
             chess = objectModel.createClub( "Chess", "734 Pine Straw Dr., Bloom, KY. 48878", new Date(), mary );
             objectModel.storeClub( chess );
             
             tennis = objectModel.createClub( "Tennis", "333 Wide St., Flower, RI. 17345", new Date(), mary );
             objectModel.storeClub( tennis );
             
             running = objectModel.createClub( "Running", "445 Pace St., Quicker, Wy. 77546", new Date(), bob );
             objectModel.storeClub( running );
             

             membership = objectModel.createMembership( joe, bridge, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( bob, bridge, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( heather, bridge, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( mary, chess, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( mary, tennis, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( julie, tennis, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( bob, tennis, new Date() );
             objectModel.storeMembership( membership );
             
             membership = objectModel.createMembership( joe, chess, new Date() );
             objectModel.storeMembership( membership );
             
             System.out.println( "Entity objects created and saved in the persistence module" );
             
         }
         catch( ClubsException ce) {
             System.err.println( "Exception: " + ce );
             ce.printStackTrace();
         }
         catch( Exception e ) {
             e.printStackTrace();
         }
         finally {
             // close the connection
             try {
                 conn.close();
             }
             catch( Exception e ) {
                 System.err.println( "Exception: " + e );
		 e.printStackTrace();
             }
         }
    }  
}

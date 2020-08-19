# ifndef VIDEOSYSTEM_HH_
# define VIDEOSYSTEM_HH_

# include "systemcomponent.hh"

class VideoSystem : public SystemComponent
{
   public:
      /**
       * Explicit constructor.
       */
      explicit VideoSystem ( void );

      /**
       * Virtual destructor.
       */
      virtual ~VideoSystem ( void );

      /**
      * Virtual member function used to initialize the SDL video system.
      * 
      * @returns "true" if the initialization succeeds, "false" otherwize.
      */
      virtual bool init ( void ) override;

      /**
       * Virtual member function used to finish the SDL video system.
       */
      virtual void terminate ( void ) override;

   private:
      bool mSystemInitialized; /**< Flag used to remember if the video system was initialized. */
};

# endif